import re
import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.sequence import pad_sequences
from konlpy.tag import Mecab
from konlpy.tag import Okt
from tensorflow.keras.preprocessing.text import Tokenizer
import tensorflow.keras.backend as K

class MultiHeadAttention(tf.keras.layers.Layer):
    def __init__(self, embedding_dim, num_heads=8):
        super(MultiHeadAttention, self).__init__()
        self.embedding_dim = embedding_dim # d_model
        self.num_heads = num_heads

        assert embedding_dim % self.num_heads == 0

        self.projection_dim = embedding_dim // num_heads
        self.query_dense = tf.keras.layers.Dense(embedding_dim)
        self.key_dense = tf.keras.layers.Dense(embedding_dim)
        self.value_dense = tf.keras.layers.Dense(embedding_dim)
        self.dense = tf.keras.layers.Dense(embedding_dim)

    def scaled_dot_product_attention(self, query, key, value):
        matmul_qk = tf.matmul(query, key, transpose_b=True)
        depth = tf.cast(tf.shape(key)[-1], tf.float32)
        logits = matmul_qk / tf.math.sqrt(depth)
        attention_weights = tf.nn.softmax(logits, axis=-1)
        output = tf.matmul(attention_weights, value)
        return output, attention_weights

    def split_heads(self, x, batch_size):
        x = tf.reshape(x, (batch_size, -1, self.num_heads, self.projection_dim))
        return tf.transpose(x, perm=[0, 2, 1, 3])

    def call(self, inputs):
        # x.shape = [batch_size, seq_len, embedding_dim]
        batch_size = tf.shape(inputs)[0]

        # (batch_size, seq_len, embedding_dim)
        query = self.query_dense(inputs)
        key = self.key_dense(inputs)
        value = self.value_dense(inputs)

        # (batch_size, num_heads, seq_len, projection_dim)
        query = self.split_heads(query, batch_size)  
        key = self.split_heads(key, batch_size)
        value = self.split_heads(value, batch_size)

        scaled_attention, _ = self.scaled_dot_product_attention(query, key, value)
        # (batch_size, seq_len, num_heads, projection_dim)
        scaled_attention = tf.transpose(scaled_attention, perm=[0, 2, 1, 3])  

        # (batch_size, seq_len, embedding_dim)
        concat_attention = tf.reshape(scaled_attention, (batch_size, -1, self.embedding_dim))
        outputs = self.dense(concat_attention)
        return outputs
    
class TransformerBlock(tf.keras.layers.Layer):
    def __init__(self, embedding_dim, num_heads, dff, rate=0.1):
        super(TransformerBlock, self).__init__()
        self.att = MultiHeadAttention(embedding_dim, num_heads)
        self.ffn = tf.keras.Sequential(
            [tf.keras.layers.Dense(dff, activation="relu"),
             tf.keras.layers.Dense(embedding_dim),]
        )
        self.layernorm1 = tf.keras.layers.LayerNormalization(epsilon=1e-6)
        self.layernorm2 = tf.keras.layers.LayerNormalization(epsilon=1e-6)
        self.dropout1 = tf.keras.layers.Dropout(rate)
        self.dropout2 = tf.keras.layers.Dropout(rate)

    def call(self, inputs, training):
        attn_output = self.att(inputs) # 첫번째 서브층 : 멀티 헤드 어텐션
        attn_output = self.dropout1(attn_output, training=training)
        out1 = self.layernorm1(inputs + attn_output) # Add & Norm
        ffn_output = self.ffn(out1) # 두번째 서브층 : 포지션 와이즈 피드 포워드 신경망
        ffn_output = self.dropout2(ffn_output, training=training)
        return self.layernorm2(out1 + ffn_output) # Add & Norm

class TokenAndPositionEmbedding(tf.keras.layers.Layer):
    def __init__(self, max_len, vocab_size, embedding_dim):
        super(TokenAndPositionEmbedding, self).__init__()
        self.token_emb = tf.keras.layers.Embedding(vocab_size, embedding_dim)
        self.pos_emb = tf.keras.layers.Embedding(max_len, embedding_dim)

    def call(self, x):
        max_len = tf.shape(x)[-1]
        positions = tf.range(start=0, limit=max_len, delta=1)
        positions = self.pos_emb(positions)
        x = self.token_emb(x)
        return x + positions

def get_custom_objects():
    return {'TokenAndPositionEmbedding': TokenAndPositionEmbedding,
            'TransformerBlock': TransformerBlock}

def korean_preprocessing(text):
    # 1. 특수문자 제거
    text = re.sub('[^가-힣ㄱ-ㅎㅏ-ㅣa-zA-Z0-9 ]', '', text)
    
    # 2. 불용어 제거
    tokenizer = Mecab()
    stopwords = ['을', '를', '이', '가', '은', '는', '의', '에', '와', '과', '도', '다', '로', '라', '지', '든지', '어디', '혹시', '어느', '여기', '저기']
    tokens = tokenizer.morphs(text)
    tokens = [token for token in tokens if not token in stopwords]
    
    # 3. 어절 분리
    words = []
    for token in tokens:
        words.extend(token.split())
    
    # 4. 표준화
    words = [word.strip() for word in words]
    words = [word for word in words if len(word) > 1]
    
    # 5. 정규화
    okt = Okt()
    normalized_words = []
    for word in words:
        normalized_words.append(okt.normalize(word))
    
    # 6. 최종 결과 반환
    result = ' '.join(normalized_words)
    return result

def preprocess(text):
    # 전처리된 문장에서 토큰 생성
    tokenizer = Tokenizer(oov_token='<UNK>')
    tokenizer.fit_on_texts([text])
    tokens = tokenizer.texts_to_sequences([text])

    padded_tokens = pad_sequences(tokens, maxlen=400, padding='post')

    return padded_tokens

def predict_result(model, text):
    # 입력된 텍스트 전처리
    text = korean_preprocessing(text)
    text = preprocess(text)

    K.set_learning_phase(1)
    custom_objects = get_custom_objects()

    # Load the model
    model = tf.keras.models.load_model('transformer_kor.h5', custom_objects=custom_objects)

    # 모델 예측 결과 출력
    prediction = model.predict(text)

    return f"{(1-prediction)*100}% 확률로 국민동의청원 사이트에서 동의를 받을 것으로 예상됩니다."
