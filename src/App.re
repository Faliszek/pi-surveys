open Belt;
open Survey;

let setValue = (questions: array(Question.t), value, id) =>
  questions->Array.map(q => q.id === id ? {...q, value} : q);

let remove = (questions: array(Question.t), id) =>
  questions->Array.keep(q => q.id !== id);

[@react.component]
let make = () => {
  let (questions: array(Question.t), setQuestions) =
    React.useState(() => [||]);

  <Layout>
    <div className={TW.[FontSize(Text3xl), Margin(Mb4)]->TW.make}>
      <Text className=TW.[FontSize(Text3xl)]> {j|Utwórz ankietę|j} </Text>
    </div>
    <Animation.Presence>
      {questions
       ->Array.mapWithIndex((index, q) =>
           <div>
             {switch (q.type_) {
              | Open =>
                <OpenQuestion
                  index
                  key={q.id}
                  value={q.value}
                  onChange={v =>
                    setQuestions(questions => setValue(questions, v, q.id))
                  }
                  onDelete={() =>
                    setQuestions(questions => remove(questions, q.id))
                  }
                />

              | Closed(answers) =>
                <CloseQuestion
                  index
                  key={q.id}
                  value={q.value}
                  onChange={v =>
                    setQuestions(questions => setValue(questions, v, q.id))
                  }
                  onDelete={() =>
                    setQuestions(questions => remove(questions, q.id))
                  }
                  onChangeAnswer={(answerId, v) =>
                    setQuestions(questions =>
                      Question.changeAnswer(
                        ~questions,
                        ~questionId=q.id,
                        ~answerId,
                        ~value=v,
                      )
                    )
                  }
                  onAddAnswer={() =>
                    setQuestions(questions =>
                      Question.addAnswer(questions, q.id)
                    )
                  }
                  onDeleteAnswer={answerId =>
                    setQuestions(questions =>
                      Question.removeAnswer(
                        ~answerId,
                        ~questionId=q.id,
                        questions,
                      )
                    )
                  }
                  answers
                />
              }}
           </div>
         )
       ->React.array}
    </Animation.Presence>
    <Button onClick={_ => setQuestions(Question.add(_, Open))}>
      <Text> {j|Dodaj pytanie otwarte|j} </Text>
    </Button>
    <Button onClick={_ => setQuestions(Question.add(_, Closed([||])))}>
      <Text> {j|Dodaj pytanie zamknięte|j} </Text>
    </Button>
  </Layout>;
};